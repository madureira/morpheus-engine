require('vstudio')

premake.api.register {
    name = "solution_items",
    scope = "workspace",
    kind = "list:string",
}

premake.override(premake.vstudio.sln2005, "projects", function(base, workspace)
    if workspace.solution_items and #workspace.solution_items > 0 then
        local solution_folder_GUID = "{2150E333-8FDC-42A3-9474-1A3956D46DE8}"
        premake.push("Project(\"" .. solution_folder_GUID .. "\") = \"Solution Items\", \"Solution Items\", \"{" .. os.uuid("Solution Items:" .. workspace.name) .. "}\"")
        premake.push("ProjectSection(SolutionItems) = preProject")

        for _, path in ipairs(workspace.solution_items) do
            premake.w(path .. " = " .. path)
        end

        premake.pop("EndProjectSection")
        premake.pop("EndProject")
    end
    base(workspace)
end)
